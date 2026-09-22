---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-22 12:22:10 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 27 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 53 |
| Sample Rate | 0.88/sec |
| Health Score | 55% |
| Threads | 8 |
| Allocations | 34 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 69 |
| Sample Rate | 1.15/sec |
| Health Score | 72% |
| Threads | 12 |
| Allocations | 29 |

<details>
<summary>CPU Timeline (2 unique values: 26-27 cores)</summary>

```
1790093758 27
1790093763 27
1790093768 26
1790093773 26
1790093778 26
1790093783 26
1790093788 26
1790093793 26
1790093798 26
1790093803 27
1790093808 27
1790093813 27
1790093818 27
1790093823 27
1790093828 27
1790093833 27
1790093838 27
1790093843 27
1790093848 27
1790093853 27
```
</details>

---

