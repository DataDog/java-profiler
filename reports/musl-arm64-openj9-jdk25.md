---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-20 12:18:20 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 53 |
| CPU Cores (end) | 54 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 12 |
| Allocations | 52 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 14 |
| Sample Rate | 0.23/sec |
| Health Score | 14% |
| Threads | 6 |
| Allocations | 12 |

<details>
<summary>CPU Timeline (3 unique values: 53-64 cores)</summary>

```
1792512815 53
1792512820 53
1792512825 53
1792512830 53
1792512835 53
1792512840 64
1792512845 64
1792512850 64
1792512855 64
1792512860 64
1792512865 64
1792512870 54
1792512875 54
1792512880 54
1792512885 54
1792512890 54
1792512895 54
1792512900 54
1792512905 54
1792512910 54
```
</details>

---

