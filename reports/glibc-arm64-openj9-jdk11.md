---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-25 00:08:18 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 24 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 212 |
| Sample Rate | 3.53/sec |
| Health Score | 221% |
| Threads | 9 |
| Allocations | 48 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 110 |
| Sample Rate | 1.83/sec |
| Health Score | 114% |
| Threads | 11 |
| Allocations | 68 |

<details>
<summary>CPU Timeline (3 unique values: 24-34 cores)</summary>

```
1795583082 24
1795583087 24
1795583092 24
1795583097 24
1795583102 24
1795583107 24
1795583112 24
1795583117 24
1795583122 24
1795583127 24
1795583132 24
1795583137 29
1795583142 29
1795583147 29
1795583152 29
1795583157 34
1795583162 34
1795583167 34
1795583172 34
1795583177 34
```
</details>

---

