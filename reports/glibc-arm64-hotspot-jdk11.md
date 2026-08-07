---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-07 13:06:39 EDT

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
| CPU Cores (start) | 14 |
| CPU Cores (end) | 25 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 113 |
| Sample Rate | 1.88/sec |
| Health Score | 117% |
| Threads | 9 |
| Allocations | 73 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 115 |
| Sample Rate | 1.92/sec |
| Health Score | 120% |
| Threads | 13 |
| Allocations | 74 |

<details>
<summary>CPU Timeline (2 unique values: 14-25 cores)</summary>

```
1786122134 14
1786122139 14
1786122144 14
1786122149 14
1786122154 14
1786122159 14
1786122164 14
1786122169 14
1786122174 14
1786122179 14
1786122184 14
1786122189 14
1786122194 14
1786122199 14
1786122204 14
1786122209 14
1786122214 25
1786122219 25
1786122224 25
1786122229 25
```
</details>

---

