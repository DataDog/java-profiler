---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-12 11:49:16 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 83 |
| CPU Cores (end) | 91 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 459 |
| Sample Rate | 7.65/sec |
| Health Score | 478% |
| Threads | 9 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 560 |
| Sample Rate | 9.33/sec |
| Health Score | 583% |
| Threads | 10 |
| Allocations | 520 |

<details>
<summary>CPU Timeline (5 unique values: 83-93 cores)</summary>

```
1794501707 83
1794501712 83
1794501717 85
1794501722 85
1794501727 85
1794501732 85
1794501737 85
1794501742 85
1794501747 85
1794501752 85
1794501757 85
1794501762 93
1794501767 93
1794501772 91
1794501777 91
1794501782 91
1794501787 91
1794501792 91
1794501797 91
1794501802 91
```
</details>

---

