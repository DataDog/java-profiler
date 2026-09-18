---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-18 04:30:59 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 25 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 546 |
| Sample Rate | 9.10/sec |
| Health Score | 569% |
| Threads | 9 |
| Allocations | 349 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 84 |
| Sample Rate | 1.40/sec |
| Health Score | 87% |
| Threads | 12 |
| Allocations | 83 |

<details>
<summary>CPU Timeline (2 unique values: 25-30 cores)</summary>

```
1789719958 25
1789719963 25
1789719968 25
1789719973 25
1789719978 25
1789719983 25
1789719988 25
1789719993 25
1789719998 25
1789720003 25
1789720008 25
1789720013 25
1789720018 25
1789720023 25
1789720028 25
1789720033 25
1789720038 25
1789720043 25
1789720048 30
1789720053 30
```
</details>

---

