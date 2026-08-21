---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-21 03:04:22 EDT

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
| CPU Cores (start) | 22 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 140 |
| Sample Rate | 2.33/sec |
| Health Score | 146% |
| Threads | 10 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 12 |
| Allocations | 64 |

<details>
<summary>CPU Timeline (3 unique values: 22-34 cores)</summary>

```
1787295676 22
1787295681 34
1787295686 34
1787295691 34
1787295696 34
1787295701 34
1787295706 34
1787295711 34
1787295716 34
1787295721 34
1787295726 34
1787295731 29
1787295736 29
1787295741 29
1787295746 29
1787295751 29
1787295756 29
1787295761 29
1787295766 29
1787295771 29
```
</details>

---

