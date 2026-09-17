---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-17 17:26:10 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 33 |
| CPU Cores (end) | 33 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 398 |
| Sample Rate | 6.63/sec |
| Health Score | 414% |
| Threads | 9 |
| Allocations | 218 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 25 |
| Sample Rate | 0.42/sec |
| Health Score | 26% |
| Threads | 8 |
| Allocations | 16 |

<details>
<summary>CPU Timeline (2 unique values: 33-64 cores)</summary>

```
1789680085 33
1789680090 33
1789680095 33
1789680100 33
1789680105 33
1789680110 33
1789680115 33
1789680120 33
1789680125 33
1789680130 33
1789680135 33
1789680140 33
1789680145 33
1789680150 33
1789680155 33
1789680160 33
1789680165 33
1789680170 33
1789680175 33
1789680180 64
```
</details>

---

