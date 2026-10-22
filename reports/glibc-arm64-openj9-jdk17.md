---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-22 06:46:58 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 58 |
| Sample Rate | 0.97/sec |
| Health Score | 61% |
| Threads | 8 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 219 |
| Sample Rate | 3.65/sec |
| Health Score | 228% |
| Threads | 11 |
| Allocations | 104 |

<details>
<summary>CPU Timeline (3 unique values: 42-47 cores)</summary>

```
1792665775 43
1792665780 43
1792665785 47
1792665790 47
1792665795 47
1792665800 47
1792665805 47
1792665810 42
1792665815 42
1792665820 42
1792665825 42
1792665830 42
1792665835 42
1792665840 42
1792665845 42
1792665850 43
1792665855 43
1792665860 43
1792665865 43
1792665870 43
```
</details>

---

