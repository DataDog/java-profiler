---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-17 17:30:50 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 28 |
| CPU Cores (end) | 33 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 125 |
| Sample Rate | 2.08/sec |
| Health Score | 130% |
| Threads | 9 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 490 |
| Sample Rate | 8.17/sec |
| Health Score | 511% |
| Threads | 14 |
| Allocations | 163 |

<details>
<summary>CPU Timeline (3 unique values: 28-64 cores)</summary>

```
1789680145 28
1789680150 28
1789680155 28
1789680160 64
1789680165 64
1789680170 64
1789680175 64
1789680180 64
1789680185 64
1789680190 64
1789680195 64
1789680200 64
1789680205 64
1789680210 64
1789680215 64
1789680220 64
1789680225 64
1789680230 64
1789680235 64
1789680240 64
```
</details>

---

