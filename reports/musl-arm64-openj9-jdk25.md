---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-25 12:18:57 EST

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 90 |
| Sample Rate | 1.50/sec |
| Health Score | 94% |
| Threads | 10 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 105 |
| Sample Rate | 1.75/sec |
| Health Score | 109% |
| Threads | 11 |
| Allocations | 79 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1795626811 64
1795626816 64
1795626821 64
1795626826 64
1795626831 64
1795626836 64
1795626841 64
1795626846 64
1795626851 64
1795626856 64
1795626861 64
1795626866 64
1795626871 64
1795626876 64
1795626881 64
1795626886 64
1795626891 64
1795626896 64
1795626901 64
1795626906 64
```
</details>

---

