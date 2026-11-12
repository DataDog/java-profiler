---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-12 07:55:48 EST

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 66 |
| Sample Rate | 1.10/sec |
| Health Score | 69% |
| Threads | 10 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 84 |
| Sample Rate | 1.40/sec |
| Health Score | 87% |
| Threads | 12 |
| Allocations | 49 |

<details>
<summary>CPU Timeline (2 unique values: 46-48 cores)</summary>

```
1794487771 46
1794487776 46
1794487781 46
1794487786 46
1794487791 46
1794487796 46
1794487801 46
1794487806 46
1794487811 46
1794487816 46
1794487821 46
1794487826 46
1794487832 46
1794487837 46
1794487842 46
1794487847 48
1794487852 48
1794487857 48
1794487862 48
1794487867 48
```
</details>

---

