---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-05 06:41:10 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 92 |
| Sample Rate | 1.53/sec |
| Health Score | 96% |
| Threads | 11 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 116 |
| Sample Rate | 1.93/sec |
| Health Score | 121% |
| Threads | 10 |
| Allocations | 69 |

<details>
<summary>CPU Timeline (3 unique values: 43-51 cores)</summary>

```
1791196541 51
1791196546 51
1791196551 51
1791196556 51
1791196561 51
1791196566 51
1791196571 51
1791196576 51
1791196581 51
1791196586 51
1791196591 49
1791196596 49
1791196601 49
1791196606 49
1791196611 49
1791196616 49
1791196621 49
1791196626 49
1791196631 49
1791196636 49
```
</details>

---

