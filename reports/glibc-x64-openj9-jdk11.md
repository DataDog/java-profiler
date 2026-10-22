---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-22 05:55:18 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 438 |
| Sample Rate | 7.30/sec |
| Health Score | 456% |
| Threads | 8 |
| Allocations | 331 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 678 |
| Sample Rate | 11.30/sec |
| Health Score | 706% |
| Threads | 9 |
| Allocations | 514 |

<details>
<summary>CPU Timeline (3 unique values: 27-30 cores)</summary>

```
1792662708 30
1792662713 30
1792662718 30
1792662723 30
1792662728 30
1792662733 30
1792662738 30
1792662743 30
1792662748 27
1792662753 27
1792662758 27
1792662763 27
1792662768 27
1792662773 27
1792662778 29
1792662783 29
1792662788 29
1792662793 29
1792662798 29
1792662803 29
```
</details>

---

