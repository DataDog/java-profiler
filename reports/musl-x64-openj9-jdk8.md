---
layout: default
title: musl-x64-openj9-jdk8
---

## musl-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-11-03 14:44:33 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 53 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 178 |
| Sample Rate | 2.97/sec |
| Health Score | 186% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 223 |
| Sample Rate | 3.72/sec |
| Health Score | 233% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 53-56 cores)</summary>

```
1793734763 53
1793734768 53
1793734773 53
1793734778 53
1793734783 55
1793734788 55
1793734793 55
1793734798 55
1793734803 55
1793734808 55
1793734813 55
1793734818 55
1793734823 55
1793734828 55
1793734833 55
1793734838 55
1793734843 55
1793734848 55
1793734853 55
1793734858 55
```
</details>

---

