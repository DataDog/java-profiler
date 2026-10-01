---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-01 00:59:49 EDT

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
| CPU Cores (start) | 28 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 183 |
| Sample Rate | 3.05/sec |
| Health Score | 191% |
| Threads | 9 |
| Allocations | 149 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 72 |
| Sample Rate | 1.20/sec |
| Health Score | 75% |
| Threads | 10 |
| Allocations | 36 |

<details>
<summary>CPU Timeline (4 unique values: 28-43 cores)</summary>

```
1790830452 28
1790830457 28
1790830462 28
1790830467 28
1790830472 28
1790830477 28
1790830482 33
1790830487 33
1790830492 33
1790830497 33
1790830502 38
1790830507 38
1790830512 38
1790830517 38
1790830522 38
1790830527 38
1790830532 38
1790830537 38
1790830542 38
1790830547 38
```
</details>

---

