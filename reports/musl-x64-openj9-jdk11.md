---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-11 06:07:53 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 77 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 572 |
| Sample Rate | 9.53/sec |
| Health Score | 596% |
| Threads | 8 |
| Allocations | 415 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 708 |
| Sample Rate | 11.80/sec |
| Health Score | 738% |
| Threads | 9 |
| Allocations | 526 |

<details>
<summary>CPU Timeline (2 unique values: 77-96 cores)</summary>

```
1794394977 96
1794394982 96
1794394987 96
1794394992 96
1794394997 96
1794395002 96
1794395007 96
1794395012 96
1794395017 77
1794395022 77
1794395027 77
1794395032 77
1794395037 77
1794395042 77
1794395047 77
1794395052 77
1794395057 77
1794395062 77
1794395067 77
1794395072 77
```
</details>

---

