---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-18 04:34:08 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 20 |
| CPU Cores (end) | 25 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 102 |
| Sample Rate | 1.70/sec |
| Health Score | 106% |
| Threads | 10 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 191 |
| Sample Rate | 3.18/sec |
| Health Score | 199% |
| Threads | 13 |
| Allocations | 136 |

<details>
<summary>CPU Timeline (2 unique values: 20-25 cores)</summary>

```
1789719913 20
1789719918 20
1789719923 20
1789719928 20
1789719933 20
1789719938 25
1789719943 25
1789719948 25
1789719953 25
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
```
</details>

---

