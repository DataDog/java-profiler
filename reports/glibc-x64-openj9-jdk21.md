---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-26 06:52:55 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 71 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 113 |
| Sample Rate | 1.88/sec |
| Health Score | 117% |
| Threads | 8 |
| Allocations | 75 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 16 |
| Sample Rate | 0.27/sec |
| Health Score | 17% |
| Threads | 6 |
| Allocations | 15 |

<details>
<summary>CPU Timeline (3 unique values: 54-71 cores)</summary>

```
1795693697 71
1795693702 71
1795693707 71
1795693712 71
1795693717 71
1795693722 71
1795693727 71
1795693732 71
1795693737 71
1795693742 71
1795693747 71
1795693752 71
1795693757 54
1795693762 54
1795693767 54
1795693772 54
1795693777 54
1795693782 56
1795693787 56
1795693792 56
```
</details>

---

