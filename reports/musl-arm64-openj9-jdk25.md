---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-21 18:25:05 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 182 |
| Sample Rate | 3.03/sec |
| Health Score | 189% |
| Threads | 11 |
| Allocations | 147 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 53 |
| Sample Rate | 0.88/sec |
| Health Score | 55% |
| Threads | 10 |
| Allocations | 42 |

<details>
<summary>CPU Timeline (3 unique values: 41-48 cores)</summary>

```
1787350864 48
1787350869 48
1787350874 48
1787350879 48
1787350884 48
1787350889 48
1787350894 48
1787350899 46
1787350904 46
1787350909 46
1787350914 46
1787350919 46
1787350924 46
1787350929 46
1787350934 46
1787350939 41
1787350944 41
1787350949 41
1787350954 41
1787350959 41
```
</details>

---

