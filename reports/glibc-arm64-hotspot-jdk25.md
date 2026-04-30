---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-04-30 14:54:46 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 72 |
| Sample Rate | 1.20/sec |
| Health Score | 75% |
| Threads | 9 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 14 |
| Allocations | 47 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1777575032 64
1777575037 64
1777575042 64
1777575047 64
1777575053 64
1777575058 64
1777575063 64
1777575068 64
1777575073 64
1777575078 64
1777575083 64
1777575088 64
1777575093 64
1777575098 64
1777575103 64
1777575108 64
1777575113 64
1777575118 64
1777575123 64
1777575128 64
```
</details>

---

