---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-18 04:34:10 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 86 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 429 |
| Sample Rate | 7.15/sec |
| Health Score | 447% |
| Threads | 9 |
| Allocations | 412 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 494 |
| Sample Rate | 8.23/sec |
| Health Score | 514% |
| Threads | 11 |
| Allocations | 521 |

<details>
<summary>CPU Timeline (3 unique values: 86-96 cores)</summary>

```
1789719998 96
1789720003 96
1789720008 96
1789720013 96
1789720018 96
1789720023 96
1789720028 96
1789720033 96
1789720038 96
1789720043 96
1789720048 96
1789720053 96
1789720058 88
1789720063 88
1789720068 88
1789720073 88
1789720078 88
1789720083 88
1789720088 88
1789720093 88
```
</details>

---

