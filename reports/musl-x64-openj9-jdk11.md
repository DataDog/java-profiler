---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-24 11:36:26 EDT

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
| CPU Cores (start) | 26 |
| CPU Cores (end) | 22 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 538 |
| Sample Rate | 8.97/sec |
| Health Score | 561% |
| Threads | 8 |
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 852 |
| Sample Rate | 14.20/sec |
| Health Score | 887% |
| Threads | 10 |
| Allocations | 524 |

<details>
<summary>CPU Timeline (5 unique values: 16-26 cores)</summary>

```
1777044688 26
1777044693 26
1777044698 26
1777044703 21
1777044708 21
1777044713 21
1777044718 21
1777044723 16
1777044728 16
1777044733 16
1777044738 16
1777044743 16
1777044748 16
1777044753 16
1777044758 16
1777044763 20
1777044768 20
1777044773 20
1777044778 20
1777044783 20
```
</details>

---

