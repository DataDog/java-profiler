---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-02 06:14:04 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 36 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 8 |
| Allocations | 52 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 9 |
| Allocations | 62 |

<details>
<summary>CPU Timeline (2 unique values: 36-48 cores)</summary>

```
1793617761 36
1793617766 36
1793617771 36
1793617776 36
1793617781 36
1793617786 36
1793617791 36
1793617796 36
1793617801 36
1793617806 36
1793617811 36
1793617816 36
1793617821 36
1793617826 36
1793617831 36
1793617836 36
1793617841 48
1793617846 48
1793617851 48
1793617856 48
```
</details>

---

