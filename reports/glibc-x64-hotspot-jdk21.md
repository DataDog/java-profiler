---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-05-06 08:41:20 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 57 |
| CPU Cores (end) | 92 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 598 |
| Sample Rate | 9.97/sec |
| Health Score | 623% |
| Threads | 9 |
| Allocations | 350 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 663 |
| Sample Rate | 11.05/sec |
| Health Score | 691% |
| Threads | 11 |
| Allocations | 501 |

<details>
<summary>CPU Timeline (5 unique values: 55-94 cores)</summary>

```
1778071067 57
1778071072 57
1778071077 57
1778071082 57
1778071087 57
1778071092 57
1778071097 57
1778071102 57
1778071107 55
1778071112 55
1778071117 55
1778071122 55
1778071127 55
1778071132 55
1778071137 94
1778071142 94
1778071147 94
1778071152 94
1778071157 94
1778071162 94
```
</details>

---

