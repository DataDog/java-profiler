---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-18 06:08:52 EST

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
| CPU Cores (start) | 88 |
| CPU Cores (end) | 69 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 480 |
| Sample Rate | 8.00/sec |
| Health Score | 500% |
| Threads | 9 |
| Allocations | 401 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 710 |
| Sample Rate | 11.83/sec |
| Health Score | 739% |
| Threads | 10 |
| Allocations | 448 |

<details>
<summary>CPU Timeline (2 unique values: 69-88 cores)</summary>

```
1794999744 88
1794999749 88
1794999754 88
1794999759 88
1794999764 88
1794999769 69
1794999774 69
1794999779 69
1794999784 69
1794999789 69
1794999794 69
1794999799 69
1794999804 69
1794999809 69
1794999814 69
1794999819 69
1794999824 69
1794999829 69
1794999834 69
1794999839 69
```
</details>

---

