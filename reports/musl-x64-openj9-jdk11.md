---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-10 18:31:14 EDT

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 62 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 519 |
| Sample Rate | 8.65/sec |
| Health Score | 541% |
| Threads | 8 |
| Allocations | 375 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 696 |
| Sample Rate | 11.60/sec |
| Health Score | 725% |
| Threads | 9 |
| Allocations | 512 |

<details>
<summary>CPU Timeline (3 unique values: 32-64 cores)</summary>

```
1786400746 32
1786400751 32
1786400756 32
1786400761 32
1786400766 32
1786400771 64
1786400776 64
1786400781 64
1786400786 64
1786400791 64
1786400796 64
1786400801 64
1786400806 64
1786400811 64
1786400816 64
1786400821 64
1786400826 64
1786400831 64
1786400836 64
1786400841 62
```
</details>

---

