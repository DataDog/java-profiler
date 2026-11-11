---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-11 05:46:23 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 45 |
| CPU Cores (end) | 37 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 60 |
| Sample Rate | 1.00/sec |
| Health Score | 62% |
| Threads | 9 |
| Allocations | 58 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 99 |
| Sample Rate | 1.65/sec |
| Health Score | 103% |
| Threads | 10 |
| Allocations | 39 |

<details>
<summary>CPU Timeline (4 unique values: 37-49 cores)</summary>

```
1794393741 45
1794393746 45
1794393751 45
1794393756 45
1794393761 45
1794393766 45
1794393771 47
1794393776 47
1794393781 47
1794393786 47
1794393791 47
1794393796 47
1794393801 47
1794393806 47
1794393811 49
1794393816 49
1794393821 49
1794393826 49
1794393831 49
1794393836 49
```
</details>

---

