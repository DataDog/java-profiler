---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-23 08:37:37 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 55 |
| CPU Cores (end) | 54 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 524 |
| Sample Rate | 8.73/sec |
| Health Score | 546% |
| Threads | 9 |
| Allocations | 403 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 703 |
| Sample Rate | 11.72/sec |
| Health Score | 732% |
| Threads | 10 |
| Allocations | 503 |

<details>
<summary>CPU Timeline (3 unique values: 54-75 cores)</summary>

```
1795440741 55
1795440746 55
1795440751 55
1795440756 55
1795440761 55
1795440766 55
1795440771 55
1795440776 55
1795440781 55
1795440786 55
1795440791 55
1795440796 75
1795440801 75
1795440806 75
1795440811 75
1795440816 75
1795440821 75
1795440826 75
1795440831 54
1795440836 54
```
</details>

---

