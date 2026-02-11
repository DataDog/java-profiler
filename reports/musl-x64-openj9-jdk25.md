---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-02-11 11:58:28 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 89 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 546 |
| Sample Rate | 9.10/sec |
| Health Score | 569% |
| Threads | 11 |
| Allocations | 417 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 784 |
| Sample Rate | 13.07/sec |
| Health Score | 817% |
| Threads | 12 |
| Allocations | 539 |

<details>
<summary>CPU Timeline (3 unique values: 89-96 cores)</summary>

```
1770828797 89
1770828802 89
1770828807 91
1770828812 91
1770828817 91
1770828822 91
1770828827 91
1770828832 91
1770828837 91
1770828842 91
1770828847 91
1770828852 91
1770828857 91
1770828862 91
1770828867 91
1770828872 91
1770828877 96
1770828882 96
1770828887 96
1770828892 96
```
</details>

---

