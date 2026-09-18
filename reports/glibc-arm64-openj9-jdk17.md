---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-18 07:52:00 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 10 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 87 |
| Sample Rate | 1.45/sec |
| Health Score | 91% |
| Threads | 11 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 12 |
| Allocations | 37 |

<details>
<summary>CPU Timeline (2 unique values: 10-30 cores)</summary>

```
1789731986 30
1789731991 30
1789731996 30
1789732001 30
1789732006 30
1789732011 30
1789732016 30
1789732021 30
1789732026 30
1789732031 30
1789732036 10
1789732041 10
1789732046 10
1789732051 10
1789732056 10
1789732061 10
1789732066 10
1789732071 10
1789732076 10
1789732081 10
```
</details>

---

