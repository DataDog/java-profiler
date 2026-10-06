---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-06 05:52:40 EDT

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
| CPU Cores (start) | 52 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 636 |
| Sample Rate | 10.60/sec |
| Health Score | 662% |
| Threads | 9 |
| Allocations | 403 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 92 |
| Sample Rate | 1.53/sec |
| Health Score | 96% |
| Threads | 15 |
| Allocations | 69 |

<details>
<summary>CPU Timeline (2 unique values: 47-52 cores)</summary>

```
1791279984 52
1791279990 52
1791279995 52
1791280000 52
1791280005 52
1791280010 52
1791280015 52
1791280020 52
1791280025 52
1791280030 52
1791280035 52
1791280040 52
1791280045 52
1791280050 52
1791280055 52
1791280060 52
1791280065 52
1791280070 52
1791280075 47
1791280080 47
```
</details>

---

