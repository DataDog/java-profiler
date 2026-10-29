---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-29 13:19:45 EDT

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
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 8 |
| Allocations | 48 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 128 |
| Sample Rate | 2.13/sec |
| Health Score | 133% |
| Threads | 12 |
| Allocations | 56 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1793293997 48
1793294002 48
1793294007 48
1793294012 48
1793294017 48
1793294022 48
1793294027 48
1793294032 48
1793294037 48
1793294042 48
1793294047 48
1793294052 48
1793294057 48
1793294062 48
1793294067 48
1793294072 48
1793294077 48
1793294082 48
1793294087 48
1793294092 48
```
</details>

---

