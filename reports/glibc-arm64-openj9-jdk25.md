---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-25 13:28:30 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 47 |
| CPU Cores (end) | 16 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 73 |
| Sample Rate | 1.22/sec |
| Health Score | 76% |
| Threads | 7 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 695 |
| Sample Rate | 11.58/sec |
| Health Score | 724% |
| Threads | 9 |
| Allocations | 523 |

<details>
<summary>CPU Timeline (2 unique values: 16-47 cores)</summary>

```
1795631040 47
1795631045 47
1795631050 47
1795631055 47
1795631060 47
1795631065 47
1795631070 47
1795631075 47
1795631080 47
1795631085 47
1795631090 47
1795631095 47
1795631100 47
1795631105 47
1795631110 47
1795631115 47
1795631120 47
1795631125 47
1795631130 47
1795631135 47
```
</details>

---

