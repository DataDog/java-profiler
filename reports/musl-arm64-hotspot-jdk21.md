---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-15 07:15:49 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 45 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 200 |
| Sample Rate | 3.33/sec |
| Health Score | 208% |
| Threads | 10 |
| Allocations | 163 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 52 |
| Sample Rate | 0.87/sec |
| Health Score | 54% |
| Threads | 11 |
| Allocations | 37 |

<details>
<summary>CPU Timeline (3 unique values: 42-45 cores)</summary>

```
1792062634 45
1792062639 45
1792062644 45
1792062649 45
1792062654 45
1792062659 45
1792062664 45
1792062669 45
1792062674 45
1792062679 45
1792062684 45
1792062689 45
1792062694 45
1792062699 45
1792062704 45
1792062709 45
1792062714 42
1792062719 42
1792062724 45
1792062729 45
```
</details>

---

