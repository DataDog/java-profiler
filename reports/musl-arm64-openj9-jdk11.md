---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-11 06:24:52 EST

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 100 |
| Sample Rate | 1.67/sec |
| Health Score | 104% |
| Threads | 10 |
| Allocations | 58 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 928 |
| Sample Rate | 15.47/sec |
| Health Score | 967% |
| Threads | 9 |
| Allocations | 491 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1794395937 48
1794395942 48
1794395948 48
1794395953 48
1794395958 48
1794395963 48
1794395968 48
1794395973 48
1794395978 48
1794395983 48
1794395988 48
1794395993 48
1794395998 48
1794396003 48
1794396008 48
1794396013 48
1794396018 48
1794396023 48
1794396028 48
1794396033 48
```
</details>

---

