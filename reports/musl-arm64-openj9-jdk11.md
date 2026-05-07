---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-05-07 13:16:16 EDT

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
| CPU Cores (start) | 59 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 121 |
| Sample Rate | 2.02/sec |
| Health Score | 126% |
| Threads | 9 |
| Allocations | 79 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 15 |
| Sample Rate | 0.25/sec |
| Health Score | 16% |
| Threads | 10 |
| Allocations | 11 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1778173716 59
1778173721 59
1778173726 59
1778173731 59
1778173736 59
1778173741 59
1778173746 59
1778173751 59
1778173756 59
1778173761 59
1778173766 59
1778173771 59
1778173776 59
1778173781 59
1778173786 59
1778173791 59
1778173796 64
1778173801 64
1778173806 64
1778173811 64
```
</details>

---

