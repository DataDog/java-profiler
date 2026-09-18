---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-18 04:28:54 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 301 |
| Sample Rate | 5.02/sec |
| Health Score | 314% |
| Threads | 11 |
| Allocations | 147 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 786 |
| Sample Rate | 13.10/sec |
| Health Score | 819% |
| Threads | 11 |
| Allocations | 445 |

<details>
<summary>CPU Timeline (2 unique values: 27-32 cores)</summary>

```
1789719913 32
1789719918 32
1789719923 32
1789719928 32
1789719933 32
1789719938 32
1789719943 32
1789719948 32
1789719953 32
1789719958 32
1789719963 32
1789719968 32
1789719973 32
1789719978 32
1789719983 32
1789719988 32
1789719993 32
1789719998 32
1789720003 32
1789720008 32
```
</details>

---

