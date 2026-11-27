---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-27 10:30:24 EST

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 54 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 100 |
| Sample Rate | 1.67/sec |
| Health Score | 104% |
| Threads | 8 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 27 |
| Sample Rate | 0.45/sec |
| Health Score | 28% |
| Threads | 10 |
| Allocations | 13 |

<details>
<summary>CPU Timeline (3 unique values: 54-64 cores)</summary>

```
1795793089 64
1795793094 64
1795793099 64
1795793104 64
1795793109 64
1795793114 64
1795793119 64
1795793124 64
1795793129 64
1795793134 64
1795793139 64
1795793144 64
1795793149 64
1795793155 64
1795793160 64
1795793165 64
1795793170 64
1795793175 64
1795793180 64
1795793185 64
```
</details>

---

