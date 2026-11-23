---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-23 04:42:45 EST

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
| CPU Cores (start) | 49 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 120 |
| Sample Rate | 2.00/sec |
| Health Score | 125% |
| Threads | 10 |
| Allocations | 54 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 27 |
| Sample Rate | 0.45/sec |
| Health Score | 28% |
| Threads | 8 |
| Allocations | 21 |

<details>
<summary>CPU Timeline (2 unique values: 29-49 cores)</summary>

```
1795426662 49
1795426667 49
1795426672 29
1795426677 29
1795426682 29
1795426687 29
1795426692 29
1795426697 29
1795426702 29
1795426707 29
1795426713 29
1795426718 29
1795426723 29
1795426728 29
1795426733 29
1795426738 29
1795426743 29
1795426748 29
1795426753 29
1795426758 29
```
</details>

---

