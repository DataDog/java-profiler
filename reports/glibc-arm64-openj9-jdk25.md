---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-27 05:15:07 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 92 |
| Sample Rate | 1.53/sec |
| Health Score | 96% |
| Threads | 12 |
| Allocations | 50 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 118 |
| Sample Rate | 1.97/sec |
| Health Score | 123% |
| Threads | 12 |
| Allocations | 64 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1777280992 64
1777280997 64
1777281002 64
1777281007 64
1777281012 64
1777281017 64
1777281022 64
1777281027 64
1777281032 64
1777281037 64
1777281042 64
1777281047 64
1777281052 64
1777281057 64
1777281062 64
1777281067 64
1777281072 64
1777281077 64
1777281082 64
1777281087 64
```
</details>

---

