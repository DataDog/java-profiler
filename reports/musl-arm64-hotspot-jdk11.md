---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-22 06:46:59 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 264 |
| Sample Rate | 4.40/sec |
| Health Score | 275% |
| Threads | 9 |
| Allocations | 188 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 64 |
| Sample Rate | 1.07/sec |
| Health Score | 67% |
| Threads | 12 |
| Allocations | 35 |

<details>
<summary>CPU Timeline (3 unique values: 42-47 cores)</summary>

```
1792665778 43
1792665783 47
1792665788 47
1792665793 47
1792665798 47
1792665803 47
1792665808 42
1792665813 42
1792665818 42
1792665823 42
1792665828 42
1792665833 42
1792665838 42
1792665843 42
1792665848 43
1792665853 43
1792665859 43
1792665864 43
1792665869 43
1792665874 43
```
</details>

---

