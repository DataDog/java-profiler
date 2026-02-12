---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-02-12 10:15:08 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 57 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 673 |
| Sample Rate | 11.22/sec |
| Health Score | 701% |
| Threads | 11 |
| Allocations | 341 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 749 |
| Sample Rate | 12.48/sec |
| Health Score | 780% |
| Threads | 13 |
| Allocations | 450 |

<details>
<summary>CPU Timeline (3 unique values: 52-57 cores)</summary>

```
1770908984 57
1770908989 57
1770908994 57
1770908999 57
1770909004 57
1770909009 57
1770909014 57
1770909019 57
1770909024 57
1770909029 52
1770909034 52
1770909039 52
1770909044 52
1770909049 52
1770909054 52
1770909059 52
1770909064 52
1770909069 52
1770909074 52
1770909079 52
```
</details>

---

