---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-18 05:54:42 EDT

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 73 |
| Sample Rate | 1.22/sec |
| Health Score | 76% |
| Threads | 10 |
| Allocations | 52 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 114 |
| Sample Rate | 1.90/sec |
| Health Score | 119% |
| Threads | 10 |
| Allocations | 74 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1792316938 46
1792316943 46
1792316948 46
1792316953 46
1792316958 46
1792316963 46
1792316968 46
1792316973 46
1792316978 46
1792316983 46
1792316988 46
1792316993 46
1792316998 51
1792317003 51
1792317008 51
1792317013 51
1792317018 51
1792317023 51
1792317028 51
1792317033 51
```
</details>

---

