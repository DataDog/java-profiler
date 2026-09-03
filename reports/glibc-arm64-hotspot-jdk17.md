---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-03 12:03:40 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 63 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 60 |
| Sample Rate | 1.00/sec |
| Health Score | 62% |
| Threads | 10 |
| Allocations | 58 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 580 |
| Sample Rate | 9.67/sec |
| Health Score | 604% |
| Threads | 10 |
| Allocations | 404 |

<details>
<summary>CPU Timeline (2 unique values: 63-64 cores)</summary>

```
1788451182 63
1788451187 63
1788451192 63
1788451197 63
1788451202 63
1788451207 63
1788451212 63
1788451217 63
1788451222 63
1788451227 63
1788451232 63
1788451237 63
1788451242 63
1788451247 63
1788451252 63
1788451257 63
1788451262 63
1788451267 63
1788451272 63
1788451277 64
```
</details>

---

