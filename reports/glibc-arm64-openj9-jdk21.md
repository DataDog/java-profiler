---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-19 11:07:54 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 56 |
| CPU Cores (end) | 62 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 89 |
| Sample Rate | 1.48/sec |
| Health Score | 92% |
| Threads | 6 |
| Allocations | 75 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 53 |
| Sample Rate | 0.88/sec |
| Health Score | 55% |
| Threads | 11 |
| Allocations | 43 |

<details>
<summary>CPU Timeline (5 unique values: 56-64 cores)</summary>

```
1787151691 56
1787151696 57
1787151701 57
1787151706 57
1787151711 59
1787151716 59
1787151721 59
1787151726 59
1787151731 59
1787151736 59
1787151741 64
1787151746 64
1787151751 62
1787151756 62
1787151761 62
1787151766 62
1787151771 62
1787151776 62
1787151781 62
1787151786 62
```
</details>

---

