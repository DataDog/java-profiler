---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-08 00:56:59 EDT

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
| CPU Cores (start) | 31 |
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 612 |
| Sample Rate | 10.20/sec |
| Health Score | 637% |
| Threads | 8 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 886 |
| Sample Rate | 14.77/sec |
| Health Score | 923% |
| Threads | 10 |
| Allocations | 472 |

<details>
<summary>CPU Timeline (2 unique values: 31-33 cores)</summary>

```
1786164785 31
1786164790 31
1786164795 31
1786164800 33
1786164805 33
1786164810 33
1786164815 33
1786164820 33
1786164825 33
1786164830 33
1786164835 33
1786164840 33
1786164845 33
1786164850 33
1786164855 33
1786164860 33
1786164865 33
1786164870 33
1786164875 33
1786164880 33
```
</details>

---

