---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-21 11:10:43 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 44 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 74 |
| Sample Rate | 1.23/sec |
| Health Score | 77% |
| Threads | 11 |
| Allocations | 54 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 65 |
| Sample Rate | 1.08/sec |
| Health Score | 68% |
| Threads | 11 |
| Allocations | 52 |

<details>
<summary>CPU Timeline (5 unique values: 41-47 cores)</summary>

```
1787324726 44
1787324731 44
1787324736 44
1787324741 44
1787324746 44
1787324751 44
1787324756 44
1787324761 44
1787324766 44
1787324771 44
1787324776 44
1787324781 44
1787324786 44
1787324791 43
1787324796 43
1787324801 42
1787324806 42
1787324811 41
1787324816 41
1787324821 41
```
</details>

---

