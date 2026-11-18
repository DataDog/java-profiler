---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-18 05:35:55 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 22 |
| CPU Cores (end) | 14 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 122 |
| Sample Rate | 2.03/sec |
| Health Score | 127% |
| Threads | 9 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 128 |
| Sample Rate | 2.13/sec |
| Health Score | 133% |
| Threads | 9 |
| Allocations | 55 |

<details>
<summary>CPU Timeline (3 unique values: 14-34 cores)</summary>

```
1794997795 22
1794997800 22
1794997805 22
1794997810 22
1794997815 22
1794997820 22
1794997825 22
1794997830 22
1794997835 22
1794997840 22
1794997845 22
1794997850 22
1794997855 22
1794997860 22
1794997865 22
1794997870 22
1794997875 34
1794997880 34
1794997885 34
1794997890 34
```
</details>

---

