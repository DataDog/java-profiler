---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-01 16:07:59 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 58 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 54 |
| Sample Rate | 0.90/sec |
| Health Score | 56% |
| Threads | 9 |
| Allocations | 55 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 58 |
| Sample Rate | 0.97/sec |
| Health Score | 61% |
| Threads | 11 |
| Allocations | 63 |

<details>
<summary>CPU Timeline (3 unique values: 58-63 cores)</summary>

```
1788293068 58
1788293073 58
1788293078 63
1788293083 63
1788293088 63
1788293093 63
1788293098 63
1788293103 63
1788293108 63
1788293113 63
1788293118 63
1788293123 63
1788293128 63
1788293133 63
1788293138 59
1788293143 59
1788293148 59
1788293153 59
1788293158 59
1788293163 59
```
</details>

---

