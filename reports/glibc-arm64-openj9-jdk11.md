---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-25 04:45:06 EDT

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
| CPU Cores (start) | 27 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 91 |
| Sample Rate | 1.52/sec |
| Health Score | 95% |
| Threads | 9 |
| Allocations | 55 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 348 |
| Sample Rate | 5.80/sec |
| Health Score | 362% |
| Threads | 13 |
| Allocations | 172 |

<details>
<summary>CPU Timeline (2 unique values: 27-64 cores)</summary>

```
1790325676 27
1790325681 64
1790325686 64
1790325691 64
1790325696 64
1790325701 64
1790325706 64
1790325711 64
1790325716 64
1790325721 64
1790325726 64
1790325731 64
1790325736 64
1790325741 64
1790325746 64
1790325751 27
1790325756 27
1790325761 27
1790325766 27
1790325771 27
```
</details>

---

