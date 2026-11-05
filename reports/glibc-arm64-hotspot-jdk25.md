---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-05 11:16:26 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 73 |
| Sample Rate | 1.22/sec |
| Health Score | 76% |
| Threads | 9 |
| Allocations | 77 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 100 |
| Sample Rate | 1.67/sec |
| Health Score | 104% |
| Threads | 13 |
| Allocations | 40 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1793895038 48
1793895043 48
1793895048 48
1793895053 48
1793895058 48
1793895063 48
1793895068 48
1793895073 48
1793895078 48
1793895083 48
1793895088 48
1793895093 48
1793895098 48
1793895103 48
1793895108 48
1793895113 48
1793895118 48
1793895123 48
1793895128 48
1793895133 48
```
</details>

---

