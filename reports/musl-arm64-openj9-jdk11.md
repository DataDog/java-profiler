---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-23 00:55:50 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 34 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 106 |
| Sample Rate | 1.77/sec |
| Health Score | 111% |
| Threads | 9 |
| Allocations | 53 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 98 |
| Sample Rate | 1.63/sec |
| Health Score | 102% |
| Threads | 10 |
| Allocations | 67 |

<details>
<summary>CPU Timeline (2 unique values: 29-34 cores)</summary>

```
1787460746 34
1787460751 34
1787460756 34
1787460761 34
1787460766 34
1787460771 34
1787460776 34
1787460781 34
1787460786 34
1787460791 34
1787460796 34
1787460801 34
1787460806 34
1787460811 34
1787460816 34
1787460821 34
1787460826 34
1787460831 34
1787460836 34
1787460841 29
```
</details>

---

