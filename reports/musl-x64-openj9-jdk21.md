---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-11 06:07:54 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 63 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 493 |
| Sample Rate | 8.22/sec |
| Health Score | 514% |
| Threads | 9 |
| Allocations | 400 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 681 |
| Sample Rate | 11.35/sec |
| Health Score | 709% |
| Threads | 10 |
| Allocations | 516 |

<details>
<summary>CPU Timeline (2 unique values: 61-63 cores)</summary>

```
1794394987 63
1794394992 63
1794394997 63
1794395002 63
1794395007 63
1794395012 63
1794395017 63
1794395022 63
1794395027 63
1794395032 63
1794395037 63
1794395042 63
1794395047 63
1794395052 63
1794395057 63
1794395062 63
1794395067 63
1794395072 63
1794395077 63
1794395082 63
```
</details>

---

