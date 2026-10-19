---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-18 21:25:11 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 25 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 62 |
| Sample Rate | 1.03/sec |
| Health Score | 64% |
| Threads | 9 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 17 |
| Sample Rate | 0.28/sec |
| Health Score | 18% |
| Threads | 12 |
| Allocations | 11 |

<details>
<summary>CPU Timeline (3 unique values: 25-32 cores)</summary>

```
1792372811 25
1792372816 25
1792372821 25
1792372826 25
1792372831 25
1792372836 25
1792372841 25
1792372846 25
1792372851 25
1792372856 25
1792372861 25
1792372866 25
1792372871 25
1792372876 30
1792372881 30
1792372886 30
1792372891 30
1792372896 30
1792372901 30
1792372906 30
```
</details>

---

