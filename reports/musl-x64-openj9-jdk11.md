---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-09 21:24:19 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 80 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 519 |
| Sample Rate | 8.65/sec |
| Health Score | 541% |
| Threads | 8 |
| Allocations | 364 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 683 |
| Sample Rate | 11.38/sec |
| Health Score | 711% |
| Threads | 9 |
| Allocations | 512 |

<details>
<summary>CPU Timeline (2 unique values: 48-80 cores)</summary>

```
1786324661 48
1786324666 48
1786324671 48
1786324676 48
1786324681 48
1786324686 48
1786324691 48
1786324696 48
1786324701 48
1786324706 48
1786324711 48
1786324716 48
1786324721 48
1786324726 48
1786324731 80
1786324736 80
1786324741 80
1786324746 80
1786324751 80
1786324756 80
```
</details>

---

