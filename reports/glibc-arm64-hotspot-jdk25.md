---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-18 04:30:57 EDT

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
| CPU Samples | 86 |
| Sample Rate | 1.43/sec |
| Health Score | 89% |
| Threads | 8 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 174 |
| Sample Rate | 2.90/sec |
| Health Score | 181% |
| Threads | 10 |
| Allocations | 110 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1789719983 48
1789719988 48
1789719993 48
1789719998 48
1789720003 48
1789720008 43
1789720013 43
1789720018 43
1789720023 43
1789720028 43
1789720033 43
1789720038 43
1789720043 43
1789720048 43
1789720053 43
1789720058 48
1789720063 48
1789720068 48
1789720073 48
1789720078 48
```
</details>

---

