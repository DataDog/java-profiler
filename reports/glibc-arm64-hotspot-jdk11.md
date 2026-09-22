---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-22 09:50:42 EDT

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
| CPU Cores (start) | 28 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 117 |
| Sample Rate | 1.95/sec |
| Health Score | 122% |
| Threads | 10 |
| Allocations | 74 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 97 |
| Sample Rate | 1.62/sec |
| Health Score | 101% |
| Threads | 13 |
| Allocations | 63 |

<details>
<summary>CPU Timeline (3 unique values: 24-36 cores)</summary>

```
1790084763 28
1790084768 28
1790084773 28
1790084778 36
1790084783 36
1790084788 36
1790084793 36
1790084798 36
1790084803 36
1790084808 36
1790084813 36
1790084818 36
1790084823 36
1790084828 36
1790084833 36
1790084838 36
1790084843 36
1790084848 36
1790084853 36
1790084858 24
```
</details>

---

