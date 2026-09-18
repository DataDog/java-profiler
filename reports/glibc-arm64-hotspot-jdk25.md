---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-18 04:33:03 EDT

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
| CPU Cores (start) | 25 |
| CPU Cores (end) | 35 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 91 |
| Sample Rate | 1.52/sec |
| Health Score | 95% |
| Threads | 11 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 87 |
| Sample Rate | 1.45/sec |
| Health Score | 91% |
| Threads | 15 |
| Allocations | 56 |

<details>
<summary>CPU Timeline (3 unique values: 25-35 cores)</summary>

```
1789719938 25
1789719943 30
1789719948 30
1789719953 30
1789719958 30
1789719963 30
1789719968 30
1789719973 30
1789719978 30
1789719983 30
1789719988 30
1789719993 30
1789719998 30
1789720003 30
1789720008 30
1789720013 30
1789720018 30
1789720023 30
1789720028 30
1789720033 30
```
</details>

---

